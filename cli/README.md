# Tree-sitter CLI
Python-urllib/3.4 20170302101307
Python-urllib/2.7 20170325195250
biNu_image_cacher_(info@binu-inc.com) 20170319122009
facebookexternalhit/1.1 20170327080438
GigablastOpenSource/1.0 20170325190123
python-requests/2.10.0 20170321104924
Mozilla/5.0_(compatible;_Google-Site-Verification/1.0) 20170319032724
Opera/9.80_(SpreadTrum;_Opera_Mini/4.4.32739/59.297;_U;_en)_Presto/2.12.423_Version/12.16 20170320133408
Opera/9.80_(Android;_Opera_Mini/7.5.31657/58.172;_U;_en)_Presto/2.12.423_Version/12.16 20170314023846
WordPress/4.5.3;_https://www.freedomleaf.com 20170314122944
Client/6.1_(org.mozilla.ios.Firefox;_build:1;_iOS_10.2.1)_Alamofire/3.5.0 20170331221513
Dispatch/0.11.1-SNAPSHOT 20170328072316
Feedly/1.0_(_http://www.feedly.com/fetcher.html;_like_FeedFetcher-Google) 20170331235951
Python-urllib/1.17 20170325034246
Mozilla/5.0_(compatible;_ImageFetcher/7.0;__http://images.weserv.nl/) 20170326143458
Google-AMPHTML 20170307200715
Opera/9.80_(MAUI_Runtime;_Opera_Mini/4.4.31998/58.203;_U;_en)_Presto/2.12.423_Version/12.16 20170316131529
rarely_used 20170326005800
Opera/9.80_(Android;_Opera_Mini/17.0.2211/58.167;_U;_en)_Presto/2.12.423_Version/12.16 20170305154954
wordpress/2.1.1 20170328102908
Mozilla/5.0_(compatible;_Dataprovider.com;) 20170306175944
WordPress/4.6.4;_http://clemencyreport.org 20170307140618
Quora_Link_Preview/1.0_(http://www.quora.com) 20170311113737
SimplePie/1.2_(Feed_Parser;_http://simplepie.org;_Allow_like_Gecko)_Build/20090627192103 20170328033126
WordPress/4.6.3;_http://clemencyreport.org 20170306195314
Mozilla/5.0_(Android_5.1.1;_Mobile;_rv:50.0)_Gecko/50.0_Firefox/50.0 20170312191143
Mozilla/4.0_(compatible) 20170314050356
Opera/9.80_(MAUI_Runtime;_Opera_Mini/4.4.31989/58.167;_U;_en)_Presto/2.12.423_Version/12.16 20170309040302
Mozilla/4.0_(vBSEO;_http://www.vbseo.com) 20170301041317
WordPress/4.7.3;_http://blog.sfgate.com/smellthetruth 20170331065351
Mozilla/5.0_Moreover/5.1_(_http://www.moreover.com;_webmaster@moreover.com) 20170307172336
Mozilla/3.0_(compatible;_Indy_Library) 20170329161842
SpuhexBot 20170306141119
Mozilla/5.0_(compatible;_ips-agent) 20170308094530
YahooCacheSystem;_YahooWebServiceClient 20170331054748
BPImageWalker/2.0_(www.bdbrandprotect.com) 20170313020946
[![crates.io badge]][crates.io] [![npmjs.com badge]][npmjs.com]

[crates.io]: https://crates.io/crates/tree-sitter-cli
[crates.io badge]: https://img.shields.io/crates/v/tree-sitter-cli.svg?color=%23B48723
[npmjs.com]: https://www.npmjs.org/package/tree-sitter-cli
[npmjs.com badge]: https://img.shields.io/npm/v/tree-sitter-cli.svg?color=%23BF4A4A

The Tree-sitter CLI allows you to develop, test, and use Tree-sitter grammars from the command line. It works on MacOS, Linux, and Windows.

### Installation

You can install the `tree-sitter-cli` with `cargo`:

```sh
cargo install tree-sitter-cli
```

or with `npm`:

```sh
npm install tree-sitter-cli
```

You can also download a pre-built binary for your platform from [the releases page].

### Dependencies

The `tree-sitter` binary itself has no dependencies, but specific commands have dependencies that must be present at runtime:

* To generate a parser from a grammar, you must have [`node`](https://nodejs.org) on your PATH.
* To run and test parsers, you must have a C and C++ compiler on your system.

### Commands

* `generate` - The `tree-sitter generate` command will generate a Tree-sitter parser based on the grammar in the current working directory. See [the documentation] for more information.

* `test` - The `tree-sitter test` command will run the unit tests for the Tree-sitter parser in the current working directory. See [the documentation] for more information.

* `parse` - The `tree-sitter parse` command will parse a file (or list of files) using Tree-sitter parsers.

[the documentation]: https://tree-sitter.github.io/tree-sitter/creating-parsers
[the releases page]: https://github.com/tree-sitter/tree-sitter/releases/latest
