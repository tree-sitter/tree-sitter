use std::collections::hash_map::Entry;

use rustc_hash::FxHashMap;

/// Decides which states of a group [`split_state_id_groups`] separates.
///
/// Besides [`Self::should_split`], a criterion can sort a group's states into classes of
/// equivalent states. These are states that never need to be split from each other, and that
/// need to be split from exactly the same states. Only the first state of each class is then
/// compared, and the rest of the class follows it.
pub trait SplitCriterion<S> {
    /// Whether `left` and `right`, from the same group, must be in different groups. This must
    /// be symmetric.
    fn should_split(&mut self, left: &S, right: &S, group_ids_by_state_id: &[u32]) -> bool;

    /// A hash of what [`Self::equivalent`] compares, if this criterion sorts states into
    /// classes.
    fn signature(&mut self, _state: &S, _group_ids_by_state_id: &[u32]) -> Option<u64> {
        None
    }

    /// Whether two states with the same signature are equivalent.
    fn equivalent(&mut self, _left: &S, _right: &S, _group_ids_by_state_id: &[u32]) -> bool {
        false
    }
}

/// Lets a function that decides [`SplitCriterion::should_split`], like the lexer's, be a
/// criterion. It has no classes, so every state is compared.
impl<S, F: FnMut(&S, &S, &[u32]) -> bool> SplitCriterion<S> for F {
    fn should_split(&mut self, left: &S, right: &S, group_ids_by_state_id: &[u32]) -> bool {
        self(left, right, group_ids_by_state_id)
    }
}

/// Splits every group from `start_group_id` on, including the groups split off from them, so
/// that no group has two states that `criterion` separates. Returns whether any group split.
///
/// A group's states are scanned in order: each state stays unless it must be split from a
/// state that stayed before it, and the states that don't stay form a new group, ordered by
/// the state they were split from, then by position.
pub fn split_state_id_groups<S>(
    states: &[S],
    state_ids_by_group_id: &mut Vec<Vec<u32>>,
    group_ids_by_state_id: &mut [u32],
    start_group_id: u32,
    criterion: &mut impl SplitCriterion<S>,
) -> bool {
    let mut result = false;
    let mut classes = GroupClasses::default();
    // The first state of each class that stays, in order.
    let mut kept = Vec::new();
    // For each class, the position in `kept` of the class it was split from, if any.
    let mut split_from = Vec::new();
    // The states that don't stay, with the position in `kept` of the class they were split
    // from.
    let mut moved = Vec::new();

    let mut group_id = start_group_id as usize;
    while group_id < state_ids_by_group_id.len() {
        let state_ids = &state_ids_by_group_id[group_id];
        // A single state has nothing to be split from.
        if state_ids.len() < 2 {
            group_id += 1;
            continue;
        }
        classes.classify(states, state_ids, group_ids_by_state_id, criterion);

        // A class follows its first state, so compare only those.
        kept.clear();
        split_from.clear();
        for &state_id in &classes.first_states {
            let state = &states[state_id as usize];
            let splitter = kept
                .iter()
                .position(|&kept_id: &u32| {
                    criterion.should_split(&states[kept_id as usize], state, group_ids_by_state_id)
                })
                .map(|position| position as u32);
            if splitter.is_none() {
                kept.push(state_id);
            }
            split_from.push(splitter);
        }

        moved.clear();
        moved.extend(
            state_ids
                .iter()
                .zip(&classes.class_ids)
                .filter_map(|(&state_id, &class_id)| {
                    Some((split_from[class_id as usize]?, state_id))
                }),
        );
        if !moved.is_empty() {
            result = true;
            // The sort is stable, so states split from the same state stay in position order.
            moved.sort_by_key(|&(splitter, _)| splitter);
            // `retain` visits the states in order.
            let mut class_ids = classes.class_ids.iter();
            state_ids_by_group_id[group_id]
                .retain(|_| split_from[*class_ids.next().unwrap() as usize].is_none());
            let new_group_id = state_ids_by_group_id.len() as u32;
            let new_group = moved
                .iter()
                .map(|&(_, state_id)| {
                    group_ids_by_state_id[state_id as usize] = new_group_id;
                    state_id
                })
                .collect();
            state_ids_by_group_id.push(new_group);
        }

        group_id += 1;
    }

    result
}

/// The states of a group, sorted into classes of equivalent states by a [`SplitCriterion`].
#[derive(Default)]
struct GroupClasses {
    /// The class of each of the group's states, by position.
    class_ids: Vec<u32>,
    /// The first state of each class, in order.
    first_states: Vec<u32>,
    /// The first class found with each signature. A state with the same signature that isn't
    /// equivalent to that class's first state gets a class of its own.
    class_ids_by_signature: FxHashMap<u64, u32>,
}

impl GroupClasses {
    /// Sorts the states of a group, `state_ids`, into classes.
    fn classify<S>(
        &mut self,
        states: &[S],
        state_ids: &[u32],
        group_ids_by_state_id: &[u32],
        criterion: &mut impl SplitCriterion<S>,
    ) {
        self.class_ids.clear();
        self.first_states.clear();
        self.class_ids_by_signature.clear();
        // With fewer than three states, classes can't save a comparison. Without a signature,
        // the criterion has no classes.
        let first_signature = if state_ids.len() >= 3 {
            criterion.signature(&states[state_ids[0] as usize], group_ids_by_state_id)
        } else {
            None
        };
        let Some(first_signature) = first_signature else {
            self.first_states.extend_from_slice(state_ids);
            self.class_ids.extend(0..state_ids.len() as u32);
            return;
        };
        self.class_ids_by_signature.insert(first_signature, 0);
        self.first_states.push(state_ids[0]);
        self.class_ids.push(0);
        for &state_id in &state_ids[1..] {
            let state = &states[state_id as usize];
            let new_class_id = self.first_states.len() as u32;
            let signature = criterion.signature(state, group_ids_by_state_id);
            let class_id = match signature.map(|s| self.class_ids_by_signature.entry(s)) {
                Some(Entry::Occupied(entry))
                    if criterion.equivalent(
                        &states[self.first_states[*entry.get() as usize] as usize],
                        state,
                        group_ids_by_state_id,
                    ) =>
                {
                    *entry.get()
                }
                Some(Entry::Vacant(entry)) => *entry.insert(new_class_id),
                Some(Entry::Occupied(_)) | None => new_class_id,
            };
            if class_id == new_class_id {
                self.first_states.push(state_id);
            }
            self.class_ids.push(class_id);
        }
    }
}
