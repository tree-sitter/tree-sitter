#!/usr/bin/env node

const fs = require('fs');
const zlib = require('zlib');
const https = require('https');
const packageJSON = require('./package.json');

// Determine the URL of the file.
const platformName = {
  'darwin': 'osx',
  'linux': 'linux',
  'win32': 'windows'
}[process.platform];
if (!platformName) {
  throw new Error(`Cannot install tree-sitter-cli for platform ${process.platform}`);
}

const archName = {
  'x64': 'x64',
  'x86': 'x86',
  'ia32': 'x86'
}[process.arch];
if (!archName) {
  throw new Error(`Cannot install tree-sitter-cli for architecture ${process.arch}`);
}

const releaseURL = `https://github.com/tree-sitter/tree-sitter/releases/download/${packageJSON.version}`;
const assetName = `tree-sitter-${platformName}-${archName}.gz`;
const assetURL = `${releaseURL}/${assetName}`;

// Remove previously-downloaded files.
const executableName = process.platform === 'win32' ? 'tree-sitter.exe' : 'tree-sitter';
if (fs.existsSync(executableName)) {
  fs.unlinkSync(executableName);
}

// Download the compressed file.
console.log(`Downloading ${assetURL}`);
const file = fs.createWriteStream(executableName);
get(assetURL, response => {
  if (response.statusCode > 299) {
    throw new Error([
      'Download failed',
      '',
      `url: ${assetURL}`,
      `status: ${response.statusCode}`,
      `headers: ${JSON.stringify(response.headers, null, 2)}`,
      '',
    ].join('\n'));
  }
  response.pipe(zlib.createGunzip()).pipe(file);
});

file.on('finish', () => {
  fs.chmodSync(executableName, '755');
});

// Follow redirects.
function get(url, callback) {
  https.get(url, response => {
    if (response.statusCode === 301 || response.statusCode === 302) {
      get(response.headers.location, callback);
    } else {
      callback(response);
    }
  });
}
