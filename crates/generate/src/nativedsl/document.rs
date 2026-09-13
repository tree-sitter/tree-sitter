use std::path::{Path, PathBuf};

use indexmap::IndexMap;
use rustc_hash::FxBuildHasher;
use serde::{Deserialize, Serialize};

use super::ast::Span;

/// Identifies a source document in a [`DocumentMap`].
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash, Serialize, Deserialize)]
#[serde(transparent)]
pub struct DocumentId(u32);

/// A byte range tied to its source document.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct DocumentSpan {
    pub document: DocumentId,
    pub span: Span,
}

impl DocumentSpan {
    #[must_use]
    pub const fn new(document: DocumentId, span: Span) -> Self {
        Self { document, span }
    }
}

/// A document borrowed from a [`DocumentMap`], paired with its [`DocumentId`].
#[derive(Clone, Copy)]
pub struct DocumentRef<'a> {
    id: DocumentId,
    documents: &'a DocumentMap,
}

impl<'a> DocumentRef<'a> {
    #[must_use]
    pub const fn id(self) -> DocumentId {
        self.id
    }

    #[must_use]
    pub fn text(self) -> &'a str {
        let (_, text) = self
            .documents
            .documents
            .get_index(self.id.0 as usize)
            .unwrap();
        text.as_str()
    }

    #[must_use]
    pub fn path(self) -> &'a Path {
        let (path, _) = self
            .documents
            .documents
            .get_index(self.id.0 as usize)
            .unwrap();
        path.as_path()
    }
}

/// Source documents used by one native DSL compilation.
#[derive(Debug, Default, Serialize, Deserialize, PartialEq, Eq)]
pub struct DocumentMap {
    #[serde(with = "indexmap::map::serde_seq")]
    documents: IndexMap<PathBuf, String, FxBuildHasher>,
}

impl DocumentMap {
    pub fn insert(&mut self, path: PathBuf, source: String) -> DocumentId {
        let (index, _) = self.documents.insert_full(path, source);
        DocumentId(index as u32)
    }

    #[must_use]
    pub const fn document(&self, id: DocumentId) -> DocumentRef<'_> {
        DocumentRef {
            id,
            documents: self,
        }
    }

    #[must_use]
    pub fn id_for_path(&self, path: &Path) -> Option<DocumentId> {
        self.documents
            .get_index_of(path)
            .map(|idx| DocumentId(idx as u32))
    }
}
