import { Component, inject } from '@angular/core';
import { HeaderComponent } from './header/header.component';
import { UserInputComponent } from './user-input/user-input.component';
import { InvestmentService } from './investment.service';
import { type InvestmentInput } from './investment-input.model';
import { InvestmentResultsComponent } from './investment-results/investment-results.component';
import { AnnualInvestment } from './investment-results/annual-investment.model';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [HeaderComponent, UserInputComponent, InvestmentResultsComponent],
  templateUrl: './app.component.html',
})
export class AppComponent {
  resultsData?: AnnualInvestment[];

  private investmentService = inject(InvestmentService);

  onCalculateInvestmentResults(data: InvestmentInput) {
    this.resultsData = this.investmentService.calculateInvestmentResults(data);
  }
}
