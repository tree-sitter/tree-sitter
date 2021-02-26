#!/usr/bin/env node

const fs = require('fs');
const zlib = require('zlib');
const https = require('https');
const packageJSON = require('./package.json');

// Determine the URL of the file.
const platformName = {
  'darwin': 'macos',
  'linux': 'linux',
  'win32': 'windows'
}[process.platform];

let archName = {
  'x64': 'x64',
  'x86': 'x86',
  'ia32': 'x86'
}[process.arch];

// ARM macs can run x64 binaries via Rosetta. Rely on that for now.
if (platformName === 'macos' && process.arch === 'arm64') {
  archName = 'x64';
}

if (!platformName || !archName) {
  console.error(
    `Cannot install tree-sitter-cli for platform ${process.platform}, architecture ${process.arch}`
  );
  process.exit(1);
}

const releaseURL = `https://github.com/tree-sitter/tree-sitter/releases/download/v${packageJSON.version}`;
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
    console.error([
      'Download failed',
      '',
      `url: ${assetURL}`,
      `status: ${response.statusCode}`,
      `headers: ${JSON.stringify(response.headers, null, 2)}`,
      '',
    ].join('\n'));
    process.exit(1);
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
