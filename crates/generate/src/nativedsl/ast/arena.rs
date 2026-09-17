//! The node arena: [`NodeId`] handles and the [`NodeArena`] that backs them.

use std::num::NonZeroU32;

use super::{IdentKind, Node, Span};

#[derive(Clone, Copy, PartialEq, Eq, Hash, Debug)]
pub struct NodeId(NonZeroU32);

impl NodeId {
    #[must_use]
    pub const fn index(self) -> usize {
        self.0.get() as usize
    }

    /// Create a `NodeId` from a 1-based index.
    ///
    /// # Panics
    ///
    /// Panics if `index` is 0.
    #[must_use]
    pub const fn from_index(index: usize) -> Self {
        Self(NonZeroU32::new(index as u32).unwrap())
    }

    #[must_use]
    pub const fn next(self) -> Self {
        // SAFETY: self.0 >= 1 and < u32::MAX (arena is bounded well below that),
        // so self.0 + 1 >= 2 and fits in u32. Always non-zero.
        debug_assert!(self.0.get() < u32::MAX);
        Self(unsafe { NonZeroU32::new_unchecked(self.0.get() + 1) })
    }
}

impl From<NodeId> for u32 {
    fn from(id: NodeId) -> Self {
        id.0.get()
    }
}

/// Arena for AST nodes and their spans.
pub struct NodeArena {
    nodes: Vec<Node>,
    spans: Vec<Span>,
}

impl NodeArena {
    #[must_use]
    pub fn new(estimated_cap: usize) -> Self {
        let mut nodes = Vec::with_capacity(estimated_cap);
        let mut spans = Vec::with_capacity(estimated_cap);
        nodes.push(Node::Unreachable);
        spans.push(Span::new(0, 0));
        Self { nodes, spans }
    }

    pub(crate) fn reserve(&mut self, additional: usize) {
        self.nodes.reserve(additional);
        self.spans.reserve(additional);
    }

    #[inline]
    pub fn push(&mut self, node: Node, span: Span) -> NodeId {
        let index = self.nodes.len() as u32;
        // SAFETY: nodes[0] is always the Unreachable sentinel, so len() >= 1. Wrapping
        // is not a realistic concern.
        let id = NodeId(unsafe { NonZeroU32::new_unchecked(index) });
        self.nodes.push(node);
        self.spans.push(span);
        id
    }

    #[inline]
    #[must_use]
    pub fn get(&self, id: NodeId) -> &Node {
        &self.nodes[id.index()]
    }

    pub fn get_mut(&mut self, id: NodeId) -> &mut Node {
        &mut self.nodes[id.index()]
    }

    /// # Safety
    ///
    /// Caller must pass a valid `id`
    #[inline]
    #[must_use]
    pub unsafe fn get_unchecked(&self, id: NodeId) -> &Node {
        unsafe { self.nodes.get_unchecked(id.index()) }
    }

    #[must_use]
    pub fn span(&self, id: NodeId) -> Span {
        self.spans[id.index()]
    }

    pub fn set(&mut self, id: NodeId, node: Node) {
        self.nodes[id.index()] = node;
    }

    #[inline]
    pub fn resolve_as(&mut self, id: NodeId, kind: IdentKind) {
        debug_assert!(matches!(
            self.get(id),
            Node::Ident(IdentKind::Unresolved(_))
        ));
        self.set(id, Node::Ident(kind));
    }

    /// Number of nodes (excluding sentinel).
    #[must_use]
    pub const fn len(&self) -> usize {
        self.nodes.len() - 1
    }

    /// The `NodeId` that the next `push` will assign. Equivalently, the
    /// exclusive end of a half-open range over all current nodes.
    #[must_use]
    pub const fn next_id(&self) -> NodeId {
        // SAFETY: nodes always contains the sentinel, so len >= 1.
        NodeId(unsafe { NonZeroU32::new_unchecked(self.nodes.len() as u32) })
    }

    /// Returns `true` if the arena contains no nodes (excluding sentinel).
    #[must_use]
    pub const fn is_empty(&self) -> bool {
        self.nodes.len() == 1
    }

    /// Iterate a half-open `[start, end)` slice of `NodeId`s and their nodes.
    ///
    /// # Safety
    ///
    /// Every index yielded by `range` must be nonzero.
    ///
    /// # Panics
    ///
    /// Panics if any index yielded by `range` exceeds the bounds of the backing arena.
    pub(super) fn iter_range(
        &self,
        range: std::ops::Range<NodeId>,
    ) -> impl Iterator<Item = (NodeId, &Node)> {
        let start = u32::from(range.start);
        let end = u32::from(range.end);

        (start..end).map(|i| {
            // SAFETY: `start` is nonzero, so every yielded index is nonzero.
            let id = NodeId(unsafe { NonZeroU32::new_unchecked(i) });
            (id, &self.nodes[i as usize])
        })
    }
}
