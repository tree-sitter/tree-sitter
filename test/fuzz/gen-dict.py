import json
import sys

def find_literals(literals, node):
  '''Recursively find STRING literals in the grammar definition'''

  if type(node) is dict:
    if 'type' in node and node['type'] == 'STRING' and 'value' in node:
      literals.add(node['value'])

    for key, value in node.iteritems():
      find_literals(literals, value)

  elif type(node) is list:
    for item in node:
      find_literals(literals, item)

def main():
  '''Generate a libFuzzer / AFL dictionary from a tree-sitter grammar.json'''
  with open(sys.argv[1]) as f:
    grammar = json.load(f)

  literals = set()
  find_literals(literals, grammar)

  for lit in sorted(literals):
    if lit:
      print '"%s"' % ''.join(['\\x%02x' % ord(b) for b in lit.encode('utf-8')])

if __name__ == '__main__':
  main()
