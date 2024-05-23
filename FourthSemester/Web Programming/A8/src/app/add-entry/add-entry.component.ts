import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { DataService } from '../data.service';
import { Entry } from '../entry';

@Component({
  selector: 'app-add-entry',
  templateUrl: './add-entry.component.html',
  styleUrl: './add-entry.component.css',
  standalone: true,
  imports: [FormsModule, CommonModule],
})
export class AddEntryComponent implements OnInit {
  title: string = '';
  comment: string = '';
  date: string = '';
  currentPage: number = 1;
  entries: Entry[] = [];
  allEntries: Entry[] = [];
  totalPages: number = 0;
  entriesPerPage: number = 4;
  isPreviousDisabled: boolean = true;
  isNextDisabled: boolean = true;
  constructor(private dataService: DataService, private router: Router) {}

  ngOnInit(): void {
    this.showEntriesByUser();
  }
  showEntriesByUser(): void {
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

  insertEntry(): void {
    this.dataService.insertEntry(this.title, this.comment, this.date).subscribe(
      (data) => {
        this.showEntriesByUser();
      },
      (error) => {
        console.error('Error inserting entry', error);
      }
    );
  }

  viewAllEntries(): void {
    this.router.navigate(['/view-entries']);
  }

  returnToProfile(): void {
    this.router.navigate(['/profile']);
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
    console.log(start, end);
    this.entries = this.allEntries.slice(start, end);

    this.isPreviousDisabled = this.currentPage === 1;
    this.isNextDisabled =
      this.currentPage === this.totalPages || this.totalPages === 0;
  }
}
