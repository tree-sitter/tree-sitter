provider treesitter {
  probe state__start(uint32_t, uint32_t);
  probe state__abandon(unsigned int, unsigned int, unsigned int);
  probe state__ran_out_of_capture_lists();
  probe parser__lex();
  probe parser__reduce();
};
