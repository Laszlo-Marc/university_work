import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { DataService } from '../data.service';
import { Entry } from '../entry';

@Component({
  selector: 'app-remove-entry',
  templateUrl: './remove-entry.component.html',
  styleUrl: './remove-entry.component.css',
  standalone: true,
  imports: [FormsModule, CommonModule],
})
export class RemoveEntryComponent implements OnInit {
  currentPage = 1;
  entriesPerPage = 4;
  entries: Entry[] = [];
  allEntries: Entry[] = [];
  totalPages = 0;
  isPreviousDisabled = true;
  isNextDisabled = true;

  constructor(private dataService: DataService, private router: Router) {}

  ngOnInit(): void {
    this.showEntriesByUser();
  }

  returnToProfile(): void {
    this.router.navigate(['/profile']);
  }
  viewAllEntries(): void {
    this.router.navigate(['/view-entries']);
  }
  showEntriesByUser() {
    if (typeof localStorage !== 'undefined') {
      const userEmail = localStorage.getItem('email');
      if (userEmail) {
        this.dataService.getEntriesByAuthor(userEmail).subscribe(
          (data) => {
            this.allEntries = data;
            this.totalPages = Math.ceil(
              this.allEntries.length / this.entriesPerPage
            );
            this.updatePagination();
          },
          (error) => {
            console.error('Error fetching user entries', error);
          }
        );
      }
    } else {
      console.error('localStorage is not available.');
    }
  }

  previousPage(): void {
    if (this.currentPage > 1) {
      this.currentPage--;
      this.updatePagination();
    }
  }

  nextPage(): void {
    if (this.currentPage < this.totalPages) {
      this.currentPage++;
      this.updatePagination();
    }
  }

  updatePagination(): void {
    const start = (this.currentPage - 1) * this.entriesPerPage;
    const end = Math.min(start + this.entriesPerPage, this.allEntries.length);
    this.entries = this.allEntries.slice(start, end);

    this.isPreviousDisabled = this.currentPage === 1;
    this.isNextDisabled =
      this.currentPage === this.totalPages || this.totalPages === 0;
  }

  removeEntry(id: number): void {
    if (confirm('Are you sure you want to delete this entry?')) {
      this.dataService.deleteEntry(id).subscribe(
        (data) => {
          console.log(data.message);
          this.showEntriesByUser();
        },
        (error) => {
          console.log(error.message);
          console.error('Error deleting entry', error);
        }
      );
    }
  }
}
