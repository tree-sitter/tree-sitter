#!/usr/bin/env bash

find src spec include examples -type f | xargs perl -pi -e 's/ +$//'
