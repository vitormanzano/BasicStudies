import { AfterContentInit, Component, ContentChild, ElementRef, Input, ViewEncapsulation, afterNextRender, afterRender, inject } from '@angular/core';

@Component({
  selector: 'app-control',
  standalone: true,
  imports: [],
  templateUrl: './control.component.html',
  styleUrl: './control.component.css',
  encapsulation: ViewEncapsulation.None,
  host: {
    class: 'control',
    '(click)': 'onClick()',
  }
})
export class ControlComponent implements AfterContentInit{
  @Input({ required: true}) label!: string;
  private el = inject(ElementRef);
  @ContentChild('input') private control?: ElementRef<HTMLInputElement | HTMLTextAreaElement>

  constructor() {
    afterRender(() => {
      console.log('afterRender');
    })

    afterNextRender(() => {
      console.log('afterNextRender');
    })
  }

  ngAfterContentInit(): void {
    // ...
  }

  onClick() {
    console.log('Clicked');
    console.log(this.el);
    console.log(this.control);
  }
}
