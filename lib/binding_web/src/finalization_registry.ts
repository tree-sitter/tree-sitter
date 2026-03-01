export function newFinalizer<T>(handler: (value: T) => void): FinalizationRegistry<T> | undefined {
  try {
    return new FinalizationRegistry(handler);
  } catch(e) {
    console.error('Unsupported FinalizationRegistry:', e);
    return;
  }
}
