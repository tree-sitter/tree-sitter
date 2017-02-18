#include "spec_helper.h"
#include "runtime/state_set.h"
#include "helpers/record_alloc.h"

START_TEST

describe("StateSet", [&]() {
  before_each([&]() {
    record_alloc::start();
  });

  after_each([&]() {
    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  it("can store a small number of states", [&]() {
    StateSet state_set = ts_state_set_new(1);
    AssertThat(state_set.length, Equals(1u));
    AssertThat(ts_state_set_contents(&state_set)[0], Equals<TSStateId>(1));

    ts_state_set_add(&state_set, 2);
    ts_state_set_add(&state_set, 3);
    ts_state_set_add(&state_set, 4);
    AssertThat(state_set.length, Equals(4u));
    AssertThat(ts_state_set_contents(&state_set)[0], Equals<TSStateId>(1));
    AssertThat(ts_state_set_contents(&state_set)[1], Equals<TSStateId>(2));
    AssertThat(ts_state_set_contents(&state_set)[2], Equals<TSStateId>(3));
    AssertThat(ts_state_set_contents(&state_set)[3], Equals<TSStateId>(4));

    ts_state_set_delete(&state_set);
  });

  it("can store a large number of states", [&]() {
    StateSet state_set = ts_state_set_new(100);
    AssertThat(state_set.length, Equals(1u));
    AssertThat(ts_state_set_contents(&state_set)[0], Equals<TSStateId>(100));

    for (TSStateId i = 1u; i < 64u; i++) {
      ts_state_set_add(&state_set, 100 + i);
      AssertThat(state_set.length, Equals(i + 1));
      AssertThat(ts_state_set_contents(&state_set)[i], Equals<TSStateId>(100 + i));
    }

    ts_state_set_delete(&state_set);
  });

  it("can be compared to other StateSets", [&]() {
    StateSet state_set1 = ts_state_set_new(100);
    ts_state_set_add(&state_set1, 1);
    ts_state_set_add(&state_set1, 2);
    ts_state_set_add(&state_set1, 3);

    StateSet state_set2 = ts_state_set_new(100);
    ts_state_set_add(&state_set2, 3);
    ts_state_set_add(&state_set2, 2);
    ts_state_set_add(&state_set2, 1);

    AssertThat(ts_state_set_eq(&state_set1, &state_set2), IsTrue());
  });
});

END_TEST
