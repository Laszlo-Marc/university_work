import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { DataService } from '../data.service';
import { Entry } from '../entry';

@Component({
  selector: 'app-update-entry',
  templateUrl: './update-entry.component.html',
  styleUrl: './update-entry.component.css',
  standalone: true,
  imports: [FormsModule, CommonModule],
})
export class UpdateEntryComponent implements OnInit {
  allEntries: Entry[] = [];
  entries: Entry[] = [];
  title: string = '';
  comment: string = '';
  date: string = '';
  currentPage: number = 1;
  entriesPerPage: number = 4;
  totalPages: number = 0;
  isPreviousDisabled: boolean = true;
  isNextDisabled: boolean = true;
  selectedEntry: Entry = {
    id: 0,
    author_email: '',
    title: '',
    comment: '',
    date: '',
  };

  constructor(private dataService: DataService, private router: Router) {}

  ngOnInit(): void {
    this.showEntriesByUser();
  }
  openUpdateForm(entry: Entry): void {
    this.selectedEntry = { ...entry }; // Copy entry data to selectedEntry for editing
  }

  updateEntry(): void {
    this.dataService
      .updateEntry(
        this.selectedEntry.id,
        this.selectedEntry.title,
        this.selectedEntry.comment,
        this.selectedEntry.date
      )
      .subscribe(
        (data) => {
          this.showEntriesByUser();
        },
        (error) => {
          console.error('Error updating entry', error);
        }
      );
  }
  showEntriesByUser(): void {
    if (typeof localStorage !== 'undefined') {
      const userEmail = localStorage.getItem('email');

      if (userEmail) {
        this.dataService
          .getEntriesByAuthor(localStorage.getItem('email') || '')
          .subscribe(
            (data) => {
              this.allEntries = data;
              this.totalPages = Math.ceil(
                this.allEntries.length / this.entriesPerPage
              );
              this.updatePagination();
            },
            (error) => {
              console.error('Error fetching entries by author', error);
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

  viewAllEntries(): void {
    this.router.navigate(['/view-entries']);
  }
  returnToProfile(): void {
    this.router.navigate(['/profile']);
  }
  updatePagination(): void {
    const start = (this.currentPage - 1) * this.entriesPerPage;
    const end = Math.min(start + this.entriesPerPage, this.allEntries.length);
    this.entries = this.allEntries.slice(start, end);

    this.isPreviousDisabled = this.currentPage === 1;
    this.isNextDisabled =
      this.currentPage === this.totalPages || this.totalPages === 0;
  }
}
