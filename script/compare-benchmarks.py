#!/usr/bin/python3
# -*- coding: utf-8 -*-

# SPDX-License-Identifier: MIT
# Copyright 2019 Matthew Krupcale <mkrupcale@matthewkrupcale.com>

import os
import re

from argparse import ArgumentParser
from collections import defaultdict

import matplotlib as mpl
import numpy as np

BENCHMARK_METRIC_UNITS = 'B/ms'

BENCHMARK_METRIC_RE_STRING = '(\d+) bytes/ms'

BENCHMARK_LANGUAGE_RE = re.compile('^Language: (.*)$', re.M)
BENCHMARK_NORMAL_EXAMPLES_RE = re.compile('^  Normal examples:$', re.M)
BENCHMARK_ERROR_EXAMPLES_RE = re.compile('^  Error examples \(mismatched languages\):$', re.M)
BENCHMARK_NORMAL_AVG_RE = re.compile('^  Average Speed \(normal\):\s+' +
                                     BENCHMARK_METRIC_RE_STRING + '$', re.M)
BENCHMARK_NORMAL_WORST_RE = re.compile('^  Worst Speed \(normal\):\s+' +
                                       BENCHMARK_METRIC_RE_STRING + '$', re.M)
BENCHMARK_ERROR_AVG_RE = re.compile('^  Average Speed \(errors\):\s+' +
                                    BENCHMARK_METRIC_RE_STRING + '$', re.M)
BENCHMARK_ERROR_WORST_RE = re.compile('^  Worst Speed \(errors\):\s+' +
                                      BENCHMARK_METRIC_RE_STRING + '$', re.M)
BENCHMARK_EXAMPLE_METRIC_RE = re.compile('^    (\S+)\s+time \d+ ms\s+speed ' +
                                         BENCHMARK_METRIC_RE_STRING + '$', re.M)
BENCHMARK_OVERALL_AGGREGATE_RE = re.compile('^Overall$', re.M)

PLOT_GROUP_COLORS = {'error': 'r',
                     'normal': 'g',
                     'aggregate': 'k'}

def _create_parser():
    parser = ArgumentParser(description="""Compares Tree-Sitter benchmark results""")
    parser.add_argument('-p', '--plot',
                        dest='p',
                        action="store_true",
                        help="Whether or not to plot figures",
                        default=False)
    parser.add_argument('-fo', '--figure-output',
                        dest='fo',
                        action="store_true",
                        help="Whether or not to output figures",
                        default=False)
    parser.add_argument('-fd', '--figure-output-dir',
                        dest='fd',
                        help="Destination directory for output figures",
                        default=os.getcwd())
    parser.add_argument('-ff', '--figure-output-format',
                        dest='ff',
                        help="Output format for figures",
                        default="eps")
    parser.add_argument('-fbe', '--figure-backend',
                        dest='fbe',
                        help="matplotlib backend")
    parser.add_argument('-nc', '--no-clobber',
                        dest='nc',
                        action="store_true",
                        help="Prevents overwrite of existing figures",
                        default=False)
    parser.add_argument('-fw', '--figure-width',
                        dest='fw',
                        type=float,
                        help="Figure width in inches",
                        default=8.)
    parser.add_argument('-fh', '--figure-height',
                        dest='fh',
                        type=float,
                        help="Figure height in inches",
                        default=6.)
    parser.add_argument('-ptitle', '--plot-title',
                        dest='ptitle',
                        help="Plot title prefix")
    parser.add_argument('-psort', '--plot-sort',
                        dest='psort',
                        action='store_true',
                        default=False,
                        help="Sort plot by time")
    parser.add_argument('-npcolor', '--no-plot-color',
                        dest='npcolor',
                        action='store_true',
                        default=False,
                        help="Do not color the plot bars and y-labels by group")
    parser.add_argument('-V', '--verbose',
                        action='store_true',
                        default=False,
                        help="Enable verbose output")
    parser.add_argument('b0',
                        help="Baseline benchmark results file")
    parser.add_argument('b1',
                        help="Updated benchmark results file")
    return parser

def save_figures(figs=None, output_dir=".", overwrite=False, file_format="eps",
                 prefix="", suffix="", fig_size=(8., 6.), **kwargs):
    """
    Saves the figures given in fig_numbers to output_directory

    Parameters

    fig_nums : list, optional
       List of integers for the figure numbers and/or
       matplotlib.figure.Figure to save
    output_dir : string, optional
        Output directory for the figures. Defaults to "."
    overwrite : bool, optional
        Whether to overwrite existing files
    file_format : string, optional
        Format in which to save figures
    prefix : string, optional
        Prefix prepended to the beginning of each file name
    suffix : string, optional
        Suffix appended to the end of each file name, before the file extension
    fig_size : tuple, optional
        Figure size in inches, (w,h)
    kwargs : dict
        Keyword args passed onto savefig
    """
    import matplotlib.pyplot as plt
    fig_nums = plt.get_fignums()
    if figs is None:
        figs = [plt.figure(fig_num) for fig_num in fig_nums]
    fig_str_format = "%0" + str(len(str(max(fig_nums)))) + "d"
    for fig in figs:
        if type(fig) is int:
            fig = plt.figure(fig)
        pathname = output_dir + "/"
        if prefix:
            pathname += prefix + "_"
        pathname += "f" + fig_str_format % fig.number
        if suffix:
            pathname += "_" + suffix
        pathname += "." + file_format
        if not overwrite:
            if os.path.isfile(pathname):
                print("File '%s' exists. Skipping" % pathname)
                continue
        fig.set_size_inches(fig_size,forward=True)
        fig.savefig(pathname, **kwargs)

def parse_args():
    return _create_parser().parse_args()

def _process_args(args):
    if args.fbe:
        mpl.use(args.fbe)

def _read_benchmark(fname):
    with open(fname, 'r') as f:
        in_bench_results = False
        in_overall_aggregate = False
        bench_language_contents = ""
        bench_overall_aggregate_contents = ""
        for line in f:
            if re.search(BENCHMARK_LANGUAGE_RE, line):
                in_bench_results = True
            if in_bench_results:
                if re.search(BENCHMARK_OVERALL_AGGREGATE_RE, line):
                    in_overall_aggregate = True
                    n_aggregate_lines = 0
                    continue
                if not in_overall_aggregate:
                    bench_language_contents += line
                else:
                    if n_aggregate_lines < 4:
                        bench_overall_aggregate_contents += line
                    else:
                        break
                    n_aggregate_lines += 1
    return bench_language_contents, bench_overall_aggregate_contents

def _find_language_blocks(bench_language_contents):
    language_blocks = []
    for m in BENCHMARK_LANGUAGE_RE.finditer(bench_language_contents):
        lang_start = m.start(0)
        language = m.group(1)
        language_blocks.append({'language':language, 'start': lang_start})
    for i, m in enumerate(BENCHMARK_ERROR_WORST_RE.finditer(bench_language_contents)):
        lang_end = m.end(0)
        language_blocks[i].update({'end': lang_end})
    return language_blocks

def _parse_normal_examples(bench_language_block):
    normal_examples = []
    lang_normal_start = re.search(BENCHMARK_NORMAL_EXAMPLES_RE, bench_language_block).end(0) + 1
    lang_normal_end = re.search(BENCHMARK_ERROR_EXAMPLES_RE, bench_language_block).start(0)
    lang_normal_block = bench_language_block[lang_normal_start:lang_normal_end]
    for m in BENCHMARK_EXAMPLE_METRIC_RE.finditer(lang_normal_block):
        name = m.group(1)
        metric = float(m.group(2))
        normal_examples.append({'name': name, 'metric': metric})
    return normal_examples

def _parse_error_examples(bench_language_block):
    error_examples = []
    lang_error_start = re.search(BENCHMARK_ERROR_EXAMPLES_RE, bench_language_block).end(0) + 1
    m = re.search(BENCHMARK_NORMAL_AVG_RE, bench_language_block)
    if m:
        lang_error_end = m.start(0)
    else:
        lang_error_end = re.search(BENCHMARK_ERROR_AVG_RE, bench_language_block).start(0)
    lang_error_block = bench_language_block[lang_error_start:lang_error_end]
    for m in BENCHMARK_EXAMPLE_METRIC_RE.finditer(lang_error_block):
        name = m.group(1)
        metric = float(m.group(2))
        error_examples.append({'name': name, 'metric': metric})
    return error_examples

def _parse_aggregate(name, regex, bench_language_block):
    name = name
    m = re.search(regex, bench_language_block)
    if m:
        metric = float(m.group(1))
    else:
        metric = None
    return {'name': name, 'metric': metric}

def _parse_aggregates(bench_language_block):
    aggregates = []
    aggregates.append(_parse_aggregate('normal_avg', BENCHMARK_NORMAL_AVG_RE, bench_language_block))
    aggregates.append(_parse_aggregate('normal_worst', BENCHMARK_NORMAL_WORST_RE, bench_language_block))
    aggregates.append(_parse_aggregate('error_avg', BENCHMARK_ERROR_AVG_RE, bench_language_block))
    aggregates.append(_parse_aggregate('error_worst', BENCHMARK_ERROR_WORST_RE, bench_language_block))
    return aggregates

def _parse_languages(bench_language_contents, language_blocks):
    bench_results = defaultdict(lambda: defaultdict(list))
    for language_block in language_blocks:
        language = language_block['language']
        start = language_block['start']
        end = language_block['end']
        bench_results[language]['normal'] = _parse_normal_examples(bench_language_contents[start:end])
        bench_results[language]['error'] = _parse_error_examples(bench_language_contents[start:end])
        bench_results[language]['aggregate'] = _parse_aggregates(bench_language_contents[start:end])
    return bench_results

def parse_benchmark(fname, verbose=False):
    bench_language_contents, bench_overall_aggregate_contents = _read_benchmark(fname)
    language_blocks = _find_language_blocks(bench_language_contents)
    if verbose:
        print("Found %d language blocks in '%s'." % (len(language_blocks), fname))
    bench_results = _parse_languages(bench_language_contents, language_blocks)
    bench_results['overall']['aggregate'] = _parse_aggregates(bench_overall_aggregate_contents)
    return bench_results

def _console_size():
    return os.popen('stty size', 'r').read().split()

def _list_of_dict_to_dict_of_ndarray(lod):
    if len(lod) != 0:
        dn = {k: np.array([d[k] for d in lod])
              for k in lod[0] if k != 'name'}
    else:
        dn = {}
    dn.update({'name': np.array([d['name'] for d in lod], dtype=object)})
    return dn

def _process_bench_data(bench_results):
    for language in bench_results:
        for group in bench_results[language]:
            bench_results[language][group] = _list_of_dict_to_dict_of_ndarray(
                bench_results[language][group])
    return bench_results

def compare_bench_data(bench_results0, bench_results1, verbose=False):
    bench_results_cmp = defaultdict(lambda: defaultdict(lambda: defaultdict()))
    if verbose:
        _, console_width = _console_size()
        example_col_width = int(console_width) * 3 // 5
        data_col_width = (int(console_width) - example_col_width) // 3
        float_precision = min(5, data_col_width - 7)
        data_table_header_format = "{:<" + str(example_col_width) + "}"
        data_table_header_format += 3 * ("{:>" + str(data_col_width) + "}")
        data_table_data_format = "{:<" + str(example_col_width) + "}"
        data_table_data_format += 3 * ("{:>" + str(data_col_width) + "." + str(float_precision) + "e}")
    for language in bench_results0:
        if verbose:
            print(("{:=^" + console_width + "}").format(''))
            if language != 'overall':
                print("language: %s" % language)
            else:
                print("overall")
            print(("{:=^" + console_width + "}").format(''))
            print(data_table_header_format.format('example',
                                                  'b0 ' + BENCHMARK_METRIC_UNITS,
                                                  'b1 ' + BENCHMARK_METRIC_UNITS,
                                                  'rel diff'))
            print(("{:-^" + console_width + "}").format(''))
        language_aggregates = bench_results0[language]['aggregate']
        group_missing_mask = language_aggregates['metric'] == None
        for group in bench_results0[language]:
            if np.any([group in name for name in language_aggregates['name'][group_missing_mask]]):
                continue
            benchmarks0 = bench_results0[language][group]
            benchmarks1 = bench_results1[language][group]
            if group is 'aggregate':
                for k in benchmarks0:
                    benchmarks0[k] = benchmarks0[k][np.invert(group_missing_mask)]
                    benchmarks1[k] = benchmarks1[k][np.invert(group_missing_mask)]
            bench_results_cmp[language][group]['name'] = benchmarks0['name']
            metric0 = benchmarks0['metric']
            metric1 = benchmarks1['metric']
            bench_results_cmp[language][group]['rel_diff'] = metric1 / metric0 - 1
            if verbose:
                for i, benchmark in enumerate(benchmarks0['name']):
                    print(data_table_data_format.format("%s: %s" % (group, benchmark),
                                                        benchmarks0['metric'][i],
                                                        benchmarks1['metric'][i],
                                                        bench_results_cmp[language][group]['rel_diff'][i]))
    return bench_results_cmp

def plot_bench_cmp(bench_results_cmp, title_prefix=None, sort=False, color_groups=True, fw=8, fh=6):
    import matplotlib.pyplot as plt
    for language in bench_results_cmp:
        if title_prefix:
            ptitle = "%s" % title_prefix
        else:
            ptitle = ""
        ptitle += "%s" % language
        plt.figure(figsize=(fw, fh))
        plt.xlabel("relative diff")
        plt.ylabel("example")
        plt.suptitle(ptitle)
        y = np.empty(0)
        x = np.empty(0)
        tick_label = np.empty(0, dtype=object)
        if color_groups:
            colors = np.empty(0, dtype='str')
        for group in bench_results_cmp[language]:
            benchmark_cmps = bench_results_cmp[language][group]
            num_benchmarks = benchmark_cmps['name'].size
            y = np.append(y, np.arange(y.size, y.size + num_benchmarks))
            x = np.append(x, benchmark_cmps['rel_diff'])
            if color_groups:
                colors = np.append(colors, [PLOT_GROUP_COLORS[group]] * num_benchmarks)
            tick_label = np.append(tick_label, ["%s: %s" % (group, name) for name in benchmark_cmps['name']])
        if sort:
            s_idx = np.argsort(x)
            x = x[s_idx]
            tick_label = tick_label[s_idx]
            if color_groups:
                colors = colors[s_idx]
        if color_groups:
            plt.barh(y, x, color=colors, tick_label=tick_label)
            for i, y_label in enumerate(plt.gca().get_yticklabels()):
                y_label.set_color(colors[i])
        else:
            plt.barh(y, x, tick_label=tick_label)
        plt.tight_layout(rect=[0, 0, 1, 0.95])

def save_bench_cmp(bench_results_cmp, args):
    import matplotlib.pyplot as plt
    fi = 1
    for language in bench_results_cmp:
        if args.ptitle:
            prefix = "%s" % args.ptitle.strip().replace(' ', '_')
        else:
            prefix = ""
        suffix = "%s_%s" % (language.replace(' ', '_'),
                            "rel_diff")
        save_figures(figs=[plt.figure(fi),], output_dir=args.fd, overwrite=not args.nc,
                     file_format=args.ff, prefix=prefix, suffix=suffix,
                     fig_size=(args.fw, args.fh))
        fi += 1

def main():
    args = parse_args()
    _process_args(args)
    bench_results0 = _process_bench_data(parse_benchmark(args.b0, args.verbose))
    bench_results1 = _process_bench_data(parse_benchmark(args.b1, args.verbose))
    bench_results_cmp = compare_bench_data(bench_results0, bench_results1, args.verbose)
    if args.p or args.fo:
        import matplotlib.pyplot as plt
        plot_bench_cmp(bench_results_cmp, args.ptitle, args.psort, not args.npcolor, args.fw, args.fh)
    if args.fo:
        save_bench_cmp(bench_results_cmp, args)
    if args.p:
        plt.show()

if __name__ == '__main__':
    main()
