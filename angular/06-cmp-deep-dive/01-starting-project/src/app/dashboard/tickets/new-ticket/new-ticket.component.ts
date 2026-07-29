import { AfterViewInit, Component, ElementRef, ViewChild, output } from '@angular/core';
import { ButtonComponent } from '../../../shared/button/button.component';
import { ControlComponent } from '../../../shared/control/control.component';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-new-ticket',
  standalone: true,
  imports: [ButtonComponent, ControlComponent, FormsModule],
  templateUrl: './new-ticket.component.html',
  styleUrl: './new-ticket.component.css'
})
export class NewTicketComponent implements AfterViewInit {
  @ViewChild('form') form?: ElementRef<HTMLFormElement>;
  add = output<{ title: string; text: string }>()

  ngAfterViewInit(): void {
     console.log('After view Init');
     this.form?.nativeElement.reset();
  }

  onSubmit(title: string, ticketText: string) {
    this.add.emit({ title: title, text: ticketText });

    this.form?.nativeElement.reset();
  }
}
