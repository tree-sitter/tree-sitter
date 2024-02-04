#!/usr/bin/env node

const fs = require('fs');
const zlib = require('zlib');
const http = require('http');
const https = require('https');
const packageJSON = require('./package.json');

// Look to a results table in https://github.com/tree-sitter/tree-sitter/issues/2196
const matrix = {
  platform: {
    'darwin': {
      name: 'macos',
      arch: {
        'arm64': { name: 'arm64' },
        'x64': { name: 'x64' },
      }
    },
    'linux': {
      name: 'linux',
      arch: {
        'arm64': { name: 'arm64' },
        'arm': { name: 'arm' },
        'x64': { name: 'x64' },
        'x86': { name: 'x86' },
        'ppc64': { name: 'powerpc64' },
      }
    },
    'win32': {
      name: 'windows',
      arch: {
        'arm64': { name: 'arm64' },
        'x64': { name: 'x64' },
        'x86': { name: 'x86' },
        'ia32': { name: 'x86' },
      }
    },
  },
}

// Determine the URL of the file.
const platform = matrix.platform[process.platform];
const arch = platform && platform.arch[process.arch];

if (!platform || !platform.name || !arch || !arch.name) {
  console.error(
    `Cannot install tree-sitter-cli for platform ${process.platform}, architecture ${process.arch}`
  );
  process.exit(1);
}

const releaseURL = `https://github.com/tree-sitter/tree-sitter/releases/download/v${packageJSON.version}`;
const assetName = `tree-sitter-${platform.name}-${arch.name}.gz`;
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
  const requestUrl = new URL(url)
  let request = https
  let requestConfig = requestUrl
  const proxyEnv = process.env['HTTPS_PROXY'] || process.env['https_proxy']

  if (proxyEnv) {
    const proxyUrl = new URL(proxyEnv)
    request = proxyUrl.protocol === 'https:' ? https : http
    requestConfig = {
      hostname: proxyUrl.hostname,
      port: proxyUrl.port,
      path: requestUrl.toString(),
      headers: {
        Host: requestUrl.hostname
      }
    }
  }

  request.get(requestConfig, response => {
    if (response.statusCode === 301 || response.statusCode === 302) {
      get(response.headers.location, callback);
    } else {
      callback(response);
    }
  });
}
