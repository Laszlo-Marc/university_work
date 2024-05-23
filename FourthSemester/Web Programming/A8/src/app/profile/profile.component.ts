import { Component } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-profile',
  standalone: true,
  imports: [],
  templateUrl: './profile.component.html',
  styleUrl: './profile.component.css',
})
export class ProfileComponent {
  username: string;

  constructor(private router: Router) {
    // Fetch username from session storage
    this.username = localStorage.getItem('email') || '';
    console.log(this.username);
    // If username is not available, navigate to login page
    if (!this.username) {
      this.router.navigate(['/login']);
    }
  }

  viewAllEntries(): void {
    this.router.navigate(['/view-entries']);
  }

  addEntry(): void {
    this.router.navigate(['/add-entry']);
  }

  removeEntry(): void {
    this.router.navigate(['/remove-entry']);
  }

  updateEntry(): void {
    this.router.navigate(['/update-entry']);
  }

  logout(): void {
    // Clear session storage and navigate to login page
    localStorage.removeItem('email');
    this.router.navigate(['/login']);
  }
}
