import { Component, input, model, output } from '@angular/core';

@Component({
  selector: 'app-rect',
  standalone: true,
  imports: [],
  templateUrl: './rect.component.html',
  styleUrl: './rect.component.css',
})
export class RectComponent {
  // Todo: Implement custom two-way binding
  //size = input.required<{ width: string; height: string }>();
  //sizeChange = output<{ width: string; height: string }>();
  size = model.required<{ width: string; height: string }>()

  onReset() {
    this.size.set({
      width: '200',
      height: '100'
    });
  }
}
