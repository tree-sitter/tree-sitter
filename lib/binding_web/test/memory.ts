import { EventEmitter } from 'events';
import { Session } from 'inspector';

const session = new Session();
session.connect();

export function gc() {
  session.post('HeapProfiler.collectGarbage');
}

export const event = new EventEmitter();

export class Finalizer<T> extends FinalizationRegistry<T> {
  constructor(handler: (value: T) => void) {
    super((value) => {
      handler(value);
      event.emit('gc');
    });
  }
}
