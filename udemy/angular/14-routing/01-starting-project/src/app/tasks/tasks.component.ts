import { Component, computed, DestroyRef, inject, input, OnInit, signal } from '@angular/core';

import { TaskComponent } from './task/task.component';
import { TasksService } from './tasks.service';
import { ActivatedRoute, ActivatedRouteSnapshot, ResolveFn, RouterLink } from '@angular/router';
import { Task } from './task/task.model';

@Component({
  selector: 'app-tasks',
  standalone: true,
  templateUrl: './tasks.component.html',
  styleUrl: './tasks.component.css',
  imports: [TaskComponent, RouterLink],
})
export class TasksComponent implements OnInit {
  private tasksService = inject(TasksService);
  // order = input<'asc' | 'desc'>();
  userId = input.required<string>();
  userTasks = computed(() => this.tasksService.allTasks()
    .filter((task) => task.userId === this.userId())
    .sort((a, b) => {
      if (this.order() === 'desc') {
        return a.id > b.id ? -1 : 1;
      }
      else {
        return a.id > b.id ? 1 : -1;
      }
    }));
  order = signal<'asc' | 'desc'>('asc');

  private activatedRoute = inject(ActivatedRoute);
  private destroyRef = inject(DestroyRef);

  ngOnInit(): void {
    const subscription = this.activatedRoute.queryParams.subscribe({
      next: (params) => (this.order.set(params['order'])),
    });

    this.destroyRef.onDestroy(() => subscription.unsubscribe());
  }
}

export const resolveUserTasks: ResolveFn<Task[]> = (
  activatedRouteSnapshot,
  routerState
) => {
  const order = activatedRouteSnapshot.queryParams['order'];
  const tasksService = inject(TasksService);
  const tasks = tasksService
    .allTasks()
    .filter(
      (task) => task.userId === activatedRouteSnapshot.paramMap.get('userId')
    );

  if (order && order === 'asc') {
    tasks.sort((a, b) => (a.id > b.id ? 1 : -1));
  }
  return tasks;
}
