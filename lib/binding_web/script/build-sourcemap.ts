import { readFileSync, writeFileSync } from 'fs';
import { SourceMapGenerator, SourceMapConsumer, RawSourceMap } from 'source-map';

async function fixSourceMap() {
  const distMap = JSON.parse(readFileSync('dist/tree-sitter.js.map', 'utf8')) as RawSourceMap;
  const distJs = readFileSync('dist/tree-sitter.js', 'utf8').split('\n');
  const finalJs = readFileSync('tree-sitter.js', 'utf8').split('\n');

  const lineMap = new Map<number, number>();

  let currentFinalLine = 0;
  for (let distLine = 0; distLine < distJs.length; distLine++) {
    const line = distJs[distLine].trim();
    if (!line) continue;

    for (let finalLine = currentFinalLine; finalLine < finalJs.length; finalLine++) {
      if (finalJs[finalLine].trim() === line) {
        lineMap.set(distLine + 1, finalLine + 1);
        currentFinalLine = finalLine;
        break;
      }
    }
  }

  const consumer = await new SourceMapConsumer(distMap);
  const generator = new SourceMapGenerator({
    file: 'tree-sitter.js',
    sourceRoot: '',
  });

  consumer.eachMapping(mapping => {
    const finalLine = lineMap.get(mapping.generatedLine);
    if (finalLine) {
      generator.addMapping({
        generated: {
          line: finalLine,
          column: mapping.generatedColumn,
        },
        original: {
          line: mapping.originalLine,
          column: mapping.originalColumn,
        },
        // Fix the source path to be relative to binding_web
        source: `src/${mapping.source.split('/').pop()}`,
        name: mapping.name,
      });
    }
  });

  for (const source of consumer.sources) {
    const content = consumer.sourceContentFor(source);
    if (content) {
      generator.setSourceContent(
        `src/${source.split('/').pop()}`,
        content,
      );
    }
  }

  consumer.destroy();
  writeFileSync('tree-sitter.js.map', generator.toString());
}

fixSourceMap().catch(console.error);
