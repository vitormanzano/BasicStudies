import { Directive, TemplateRef, ViewContainerRef, effect, inject, input } from '@angular/core';
import { Permission } from './auth.model';
import { AuthService } from './auth.service';

@Directive({
  selector: '[appAuth]',
  standalone: true
})
export class AuthDirective { // Structural directive
  userType = input.required<Permission>({ alias: 'appAuth' });
  private authService = inject(AuthService);
  private templateRef = inject(TemplateRef); // gives the directive access to the content of the <ng-template> it is applied to
  private viewContainerRef = inject(ViewContainerRef); // represents the location in the DOM where the directive can render that template.

  constructor() {
    effect(() => { // effect() Do something when some signal changes
      if (this.authService.activePermission() == this.userType()) {
        this.viewContainerRef.createEmbeddedView(this.templateRef);
      } else {
        this.viewContainerRef.clear();
      }
    });
  }

}
