import { Injectable, signal } from '@angular/core';
import { BehaviorSubject } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class MessagesService {
  // messages$ = new BehaviorSubject<string[]>([]);
  private messages = signal<string[]>([]);
  allMessages = this.messages.asReadonly();

  addMessage(message: string) {
    this.messages.update(oldMessages => [...oldMessages]);
  }
}
