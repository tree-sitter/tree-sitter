#!/usr/bin/env bash

find src spec include examples/grammars -type f | xargs perl -pi -e 's/ +$//'
