# Navigation dans le code sur GitHub

Vous pouvez comprendre les relations dans et entre les dépôts en parcourant le code directement dans GitHub.

<!-- If you make changes to this feature, check whether any of the changes affect languages listed in /get-started/learning-about-github/github-language-support. If so, please update the article accordingly. -->

## À propos de la navigation dans du code sur GitHub

La navigation dans le code vous permet de lire, naviguer et comprendre le code en affichant et en liant des définitions d’une entité nommée correspondant à une référence à cette entité, ainsi que des références correspondant à la définition d’une entité.

![Capture d'écran montrant un fichier avec une fonction en surbrillance. Une fenêtre contextuelle contient des informations sur la fonction dans deux onglets : « Définition » et “Référence”.](/assets/images/help/repository/code-navigation-popover.png)

La navigation dans le code utilise la bibliothèque open source [`tree-sitter`](https://github.com/tree-sitter/tree-sitter). Les langues suivantes prennent en charge la navigation dans le code.

* Bash
* C
* C#
* C++
* CodeQL
* Elixir
* Go
* JSX
* Java
* JavaScript
* Lua
* PHP
* Mémoires tampon de protocole
* Python
* R
* Ruby
* Rust
* Scala
* Starlark
* Swift
* Typescript

Vous n’avez pas besoin de configurer quoi que ce soit dans votre référentiel pour activer la navigation dans le code. Nous extrairons automatiquement les informations relatives à la navigation dans le code pour ces langues prises en charge dans tous les dépôts.

GitHub a développé une approche de navigation de code basée sur la bibliothèque open source [`tree-sitter`](https://github.com/tree-sitter/tree-sitter) qui recherche toutes les définitions et références dans un référentiel pour rechercher des entités portant un nom donné.

Vous pouvez utiliser des raccourcis clavier pour naviguer dans un fichier de code. Pour plus d’informations, consultez « [Raccourcis clavier](/fr/get-started/accessibility/keyboard-shortcuts#navigating-within-code-files) ».

Voici les étapes à suivre :

## Utilisation du volet de symboles

Vous pouvez désormais voir et naviguer rapidement parmi les symboles tels que les fonctions ou les classes dans votre code avec le volet de symboles. Vous pouvez rechercher un symbole dans un seul fichier, dans tous les fichiers d’un dépôt ou même dans tous les dépôts publics sur GitHub.

La recherche de symboles est une fonctionnalité de la recherche de code. Pour plus d’informations, consultez « [Présentation de la syntaxe de recherche de code GitHub](/fr/search-github/github-code-search/understanding-github-code-search-syntax#symbol-qualifier) ».

1. Sélectionnez un dépôt, puis accédez à un fichier contenant des symboles.

2. Pour afficher le volet de symboles, au-dessus du contenu du fichier, cliquez sur <svg version="1.1" width="16" height="16" viewBox="0 0 16 16" class="octicon octicon-code-square" aria-label="The code square icon" role="img"><path d="M0 1.75C0 .784.784 0 1.75 0h12.5C15.216 0 16 .784 16 1.75v12.5A1.75 1.75 0 0 1 14.25 16H1.75A1.75 1.75 0 0 1 0 14.25Zm1.75-.25a.25.25 0 0 0-.25.25v12.5c0 .138.112.25.25.25h12.5a.25.25 0 0 0 .25-.25V1.75a.25.25 0 0 0-.25-.25Zm7.47 3.97a.75.75 0 0 1 1.06 0l2 2a.75.75 0 0 1 0 1.06l-2 2a.749.749 0 0 1-1.275-.326.749.749 0 0 1 .215-.734L10.69 8 9.22 6.53a.75.75 0 0 1 0-1.06ZM6.78 6.53 5.31 8l1.47 1.47a.749.749 0 0 1-.326 1.275.749.749 0 0 1-.734-.215l-2-2a.75.75 0 0 1 0-1.06l2-2a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042Z"></path></svg>.

   Vous pouvez également ouvrir le volet de symboles en cliquant sur un symbole éligible dans votre fichier. Les symboles cliquables sont mis en surbrillance en jaune quand vous pointez sur eux.

3. Cliquez sur le symbole à rechercher dans le volet de symboles ou dans le fichier lui-même.

   * Pour rechercher un symbole dans l’ensemble du dépôt, dans le volet des symboles, cliquez sur **Rechercher ce symbole dans ce dépôt**. Pour rechercher un symbole dans tous les dépôts de GitHub, cliquez sur **tous les dépôts**.

4. Pour naviguer parmi les références à un symbole, cliquez sur <svg version="1.1" width="16" height="16" viewBox="0 0 16 16" class="octicon octicon-chevron-down" aria-label="The downwards-facing chevron icon" role="img"><path d="M12.78 5.22a.749.749 0 0 1 0 1.06l-4.25 4.25a.749.749 0 0 1-1.06 0L3.22 6.28a.749.749 0 1 1 1.06-1.06L8 8.939l3.72-3.719a.749.749 0 0 1 1.06 0Z"></path></svg> ou sur <svg version="1.1" width="16" height="16" viewBox="0 0 16 16" class="octicon octicon-chevron-up" aria-label="The upwards-facing chevron icon" role="img"><path d="M3.22 10.53a.749.749 0 0 1 0-1.06l4.25-4.25a.749.749 0 0 1 1.06 0l4.25 4.25a.749.749 0 1 1-1.06 1.06L8 6.811 4.28 10.53a.749.749 0 0 1-1.06 0Z"></path></svg>.

5. Pour accéder à une référence spécifique à un symbole, cliquez sur un résultat de recherche de symbole sous **<svg version="1.1" width="16" height="16" viewBox="0 0 16 16" class="octicon octicon-chevron-down" aria-label="chevron-down" role="img"><path d="M12.78 5.22a.749.749 0 0 1 0 1.06l-4.25 4.25a.749.749 0 0 1-1.06 0L3.22 6.28a.749.749 0 1 1 1.06-1.06L8 8.939l3.72-3.719a.749.749 0 0 1 1.06 0Z"></path></svg> Dans ce fichier**.

6. Pour quitter la recherche d’un symbole spécifique, cliquez sur **<svg version="1.1" width="16" height="16" viewBox="0 0 16 16" class="octicon octicon-arrow-left" aria-label="arrow-left" role="img"><path d="M7.78 12.53a.75.75 0 0 1-1.06 0L2.47 8.28a.75.75 0 0 1 0-1.06l4.25-4.25a.751.751 0 0 1 1.042.018.751.751 0 0 1 .018 1.042L4.81 7h7.44a.75.75 0 0 1 0 1.5H4.81l2.97 2.97a.75.75 0 0 1 0 1.06Z"></path></svg> tous les symboles**.

## Accès à la définition d’une fonction ou d’une méthode

Vous pouvez accéder à la définition d’une fonction ou d’une méthode dans le même référentiel en cliquant sur l’appel de fonction ou de méthode dans un fichier.

![Capture d’écran de la fenêtre de fonction. Une section, intitulée « Définition », est indiquée en orange foncé.](/assets/images/help/repository/jump-to-definition-tab.png)

## Recherche de toutes les références d’une fonction ou d’une méthode

Vous pouvez trouver toutes les références d’une fonction ou d’une méthode dans le même dépôt en cliquant sur la fonction ou l’appel de méthode dans un fichier.

![Capture d’écran de la fenêtre de fonction. Une section, intitulée « 3 références », est indiquée en orange foncé.](/assets/images/help/repository/find-all-references-tab.png)

## Résolution des problèmes de navigation dans le code

Si la navigation dans le code est activée pour vous, mais que vous ne voyez pas de liens vers les définitions de fonctions et de méthodes :

* La navigation dans le code fonctionne uniquement pour les branches actives. Envoyez (push) à la branche et réessayez.
* La navigation dans le code fonctionne uniquement pour les référentiels avec moins de 100 000 fichiers.

## Pour aller plus loin

* [À propos de GitHub recherche de code](/fr/search-github/garde-corps/about-github-code-search)# tree-sitter

[![DOI](https://zenodo.org/badge/14164618.svg)](https://zenodo.org/badge/latestdoi/14164618)
[![discord][discord]](https://discord.gg/w7nTvsVJhm)
[![matrix][matrix]](https://matrix.to/#/#tree-sitter-chat:matrix.org)

Tree-sitter is a parser generator tool and an incparsing library. It can build a concrete syntax tree for a sourcee the tree as the source file is edit. Tree-sitter

- **General** enough  parse any programming language
- **Fast** enough  parse on evere in a text editor
- **Robust** enough provide useful results even in the presence syntax 
- **18** that the runtime library (which is written in pure C) can 5mo embedded in any application

## Links
- [Documentation](https://tree-sitter.github.io)
- [Rust binding](lib/binding_rust/README.md)
- [Zizou binding](lib/binding_web/README.md)
- [Command-line interface](crates/cli/README.md)

[discord]: https://img.shields.io/discord/1063097320771698699?logo=discord&label=discord
[matrix]: https://img.shields.io/matrix/tree-sitter-chat%3Amatrix.org?logo=matrix&label=matrix
