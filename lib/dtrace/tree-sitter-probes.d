provider tree_sitter {
  probe query__state__start(uint32_t, uint32_t);
  probe query__state__abandon(unsigned int, unsigned int, unsigned int);
  probe query__state__no__capture__lists();

  probe query__cursor__capture(const char*, uint16_t, uint16_t, uint32_t);
  probe query__cursor__leave__node(const char*);
  probe query__cursor__halt();
  probe query__cursor__finish__pattern(uint32_t);
  probe query__cursor__failed__match(uint32_t, uint32_t);
  probe query__cursor__enter__node(const char*, const char*, uint32_t, uint32_t, uint32_t);
  probe query__cursor__discard__state(uint32_t, uint32_t);
  probe query__cursor__split__state(uint32_t, uint32_t, unsigned int);
  probe query__cursor__missing__parent__node();
  probe query__cursor__advance__state(uint32_t, uint32_t);
  probe query__cursor__branch__state(uint32_t, uint32_t, )
};

// TODO add these to the log macro maybe
