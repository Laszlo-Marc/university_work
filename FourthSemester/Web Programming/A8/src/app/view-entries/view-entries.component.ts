import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { DataService } from '../data.service';
import { Entry } from '../entry';
@Component({
  selector: 'app-view-entries',
  templateUrl: './view-entries.component.html',
  standalone: true,
  styleUrl: './view-entries.component.css',
  imports: [CommonModule, FormsModule],
})
export class ViewEntriesComponent implements OnInit {
  allEntries: Entry[] = [];
  entries: Entry[] = [];
  authorFilter: string = '';
  titleFilter: string = '';
  currentPage: number = 1;
  entriesPerPage: number = 4;
  totalPages: number = 0;
  isPreviousDisabled: boolean = true;
  isNextDisabled: boolean = true;

  constructor(private dataService: DataService, private router: Router) {}

  ngOnInit(): void {
    this.getAllEntries();
  }

  getAllEntries(): void {
    this.dataService.getAllEntries().subscribe(
      (data) => {
        this.allEntries = data;
        this.totalPages = Math.ceil(
          this.allEntries.length / this.entriesPerPage
        );
        this.updatePagination();
      },
      (error) => {
        console.error('Error fetching entries', error);
      }
    );
  }

  filterByAuthor(): void {
    this.dataService.searchByAuthor(this.authorFilter).subscribe(
      (data) => {
        this.allEntries = data;
        this.currentPage = 1;
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

  filterByTitle(): void {
    this.dataService.getEntriesByTitle(this.titleFilter).subscribe(
      (data) => {
        this.allEntries = data;
        this.currentPage = 1;
        this.totalPages = Math.ceil(
          this.allEntries.length / this.entriesPerPage
        );
        this.updatePagination();
      },
      (error) => {
        console.log(error.message);
        console.error('Error fetching entries by title', error);
      }
    );
  }

  filterByUser(): void {
    this.dataService
      .getEntriesByAuthor(localStorage.getItem('email') || '')
      .subscribe(
        (data) => {
          this.allEntries = data;
          this.currentPage = 1;
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

  returnToProfile(): void {
    this.router.navigate(['/profile']);
  }
}
