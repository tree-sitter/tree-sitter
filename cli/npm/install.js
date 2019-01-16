#!/usr/bin/env node

const fs = require('fs');
const https = require('https');
const execFileSync = require('child_process').execFileSync;
const packageJSON = require('./package.json');

// Determine the URL of the file.
const isWindows = process.platform === 'win32';
const platformName = {
  'darwin': 'osx',
  'linux': 'linux',
  'win32': 'windows'
}[process.platform];
if (!platformName) {
  throw new Error(`Cannot install tree-sitter-cli for platform ${process.platform}`);
}
const releaseURL = `https://github.com/tree-sitter/tree-sitter/releases/download/${packageJSON.version}`;
const assetExtension = isWindows ? 'zip' : 'tar.gz';
const assetName = `tree-sitter-${platformName}-${process.arch}.${assetExtension}`;
const assetURL = `${releaseURL}/${assetName}`;

// Remove previously-downloaded files.
const executableName = isWindows ? 'tree-sitter.exe' : 'tree-sitter';
if (fs.existsSync(executableName)) {
  fs.unlinkSync(executableName);
}
if (fs.existsSync(assetName)) {
  fs.unlinkSync(assetName);
}

// Download the compressed file.
console.log(`Downloading ${assetURL}`);
const file = fs.createWriteStream(assetName);
get(assetURL, response => {
  if (response.statusCode > 299) {
    throw new Error([
      'Download failed',
      '',
      `url: ${url}`,
      `status: ${response.statusCode}`,
      `headers: ${JSON.stringify(response.headers, null, 2)}`,
      '',
    ].join('\n'));
  }

  response.pipe(file);
});

// Extract the file.
file.on('finish', () => {
  console.log(`Extracting ${assetName}`);
  if (isWindows) {
    execFileSync('7z', ['e', assetName]);
  } else {
    execFileSync('tar', ['xzf', assetName]);
  }
  fs.unlinkSync(assetName);
  console.log(`Done`);
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
