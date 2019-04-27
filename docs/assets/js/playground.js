const codeInput = document.getElementById('code-input');
const languageSelect = document.getElementById('language-select');
const loggingCheckbox = document.getElementById('logging-checkbox');
const outputContainer = document.getElementById('output-container');
const updateTimeSpan = document.getElementById('update-time');
const demoContainer = document.getElementById('playground-container');

const languagesByName = {};

let tree;
let parser;
let codeEditor;
let queryEditor;
let languageName;
let highlightedNodeLink;

main();

async function main() {
  await TreeSitter.init();
  parser = new TreeSitter();
  codeEditor = CodeMirror.fromTextArea(codeInput, {
    lineNumbers: true,
    showCursorWhenSelecting: true
  });

  languageName = languageSelect.value;
  codeEditor.on('changes', handleCodeChange);
  codeEditor.on('cursorActivity', handleCursorMovement);
  loggingCheckbox.addEventListener('change', handleLoggingChange);
  languageSelect.addEventListener('change', handleLanguageChange);
  outputContainer.addEventListener('click', handleTreeClick);

  await handleLanguageChange();
  demoContainer.style.visibility = 'visible';
}

async function handleLanguageChange() {
  const newLanguageName = languageSelect.value;
  if (!languagesByName[newLanguageName]) {
    const url = `${LANGUAGE_BASE_URL}/tree-sitter-${newLanguageName}.wasm`
    languageSelect.disabled = true;
    try {
      languagesByName[newLanguageName] = await TreeSitter.Language.load(url);
    } catch (e) {
      console.error(e);
      languageSelect.value = languageName;
      return
    } finally {
      languageSelect.disabled = false;
    }
  }

  tree = null;
  languageName = newLanguageName;
  parser.setLanguage(languagesByName[newLanguageName]);
  handleCodeChange();
}

function handleLoggingChange() {
  if (loggingCheckbox.checked) {
    parser.setLogger(console.log);
  } else {
    parser.setLogger(null);
  }
}

function handleCodeChange(editor, changes) {
  let start;
  if (tree && changes) {
    start = performance.now();
    for (const change of changes) {
      const edit = treeEditForEditorChange(change);
      tree.edit(edit);
    }
  } else {
    start = performance.now();
  }
  const newTree = parser.parse(codeEditor.getValue() + '\n', tree);
  tree && tree.delete();
  tree = newTree;
  updateTimeSpan.innerText = `${(performance.now() - start).toFixed(1)} ms`;
  renderTree();
}

function handleTreeClick(event) {
  if (event.target.className === 'tree-link') {
    event.preventDefault();
    const row = parseInt(event.target.dataset.row);
    const column = parseInt(event.target.dataset.column);
    codeEditor.setCursor({line: row, ch: column});
    codeEditor.focus();
  }
}

function treeEditForEditorChange(change) {
  const oldLineCount = change.removed.length;
  const newLineCount = change.text.length;
  const lastLineLength = change.text[newLineCount - 1].length;

  const startPosition = {row: change.from.line, column: change.from.ch};
  const oldEndPosition = {row: change.to.line, column: change.to.ch};
  const newEndPosition = {
    row: startPosition.row + newLineCount - 1,
    column: newLineCount === 1
      ? startPosition.column + lastLineLength
      : lastLineLength
  };

  const startIndex = codeEditor.indexFromPos(change.from);
  let newEndIndex = startIndex + newLineCount - 1;
  let oldEndIndex = startIndex + oldLineCount - 1;
  for (let i = 0; i < newLineCount; i++) newEndIndex += change.text[i].length;
  for (let i = 0; i < oldLineCount; i++) oldEndIndex += change.removed[i].length;

  return {
    startIndex, oldEndIndex, newEndIndex,
    startPosition, oldEndPosition, newEndPosition
  };
}

var handleCursorMovement = debounce(() => {
  if (highlightedNodeLink) {
    highlightedNodeLink.classList.remove('highlighted');
    highlightedNodeLink = null;
  }

  const selection = codeEditor.getDoc().listSelections()[0];
  let start = {row: selection.anchor.line, column: selection.anchor.ch};
  let end = {row: selection.head.line, column: selection.head.ch};
  if (
    start.row > end.row ||
    (
      start.row === end.row &&
      start.column > end.column
    )
  ) {
    let swap = end;
    end = start;
    start = swap;
  }
  const node = tree.rootNode.namedDescendantForPosition(start, end);
  const link = document.querySelector(`.tree-link[data-id="${node[0]}"]`);
  link.classList.add('highlighted');
  highlightedNodeLink = link;

  $(outputContainer).animate({
    scrollTop: Math.max(0, link.offsetTop - outputContainer.clientHeight / 2)
  }, 200);
}, 300);

var renderTree = debounce(() => {
  let result = "";
  renderNode(tree.rootNode, 0);
  function renderNode(node, indentLevel) {
    let space = '  '.repeat(indentLevel);
    const type = node.type;
    const start = node.startPosition;
    const end = node.endPosition;
    result += space;
    result += "(<a class='tree-link' href='#' ";
    result += `data-id="${node[0]}" data-row=${start.row} data-column=${start.column}>${type}</a>`
    result += `[${start.row + 1}, ${start.column}] - [${end.row + 1}, ${end.column}]`;
    if (node.namedChildren.length > 0) {
      for (let i = 0, n = node.namedChildren.length; i < n; i++) {
        result += '\n';
        renderNode(node.namedChildren[i], indentLevel + 1);
      }
    }
    result += ')';
  }

  outputContainer.innerHTML = result;
}, 200);

function debounce(func, wait, immediate) {
	var timeout;
	return function() {
		var context = this, args = arguments;
		var later = function() {
			timeout = null;
			if (!immediate) func.apply(context, args);
		};
		var callNow = immediate && !timeout;
		clearTimeout(timeout);
		timeout = setTimeout(later, wait);
		if (callNow) func.apply(context, args);
	};
};
