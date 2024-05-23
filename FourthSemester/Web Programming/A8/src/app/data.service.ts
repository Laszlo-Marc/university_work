import { HttpClient, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class DataService {
  private apiUrl = 'http://localhost/A7-R/db/schema.php';

  constructor(private http: HttpClient) {}

  getAllEntries(): Observable<any> {
    return this.http.get<any>(`${this.apiUrl}?action=selectAllEntries`);
  }

  getEntriesByAuthor(author: string): Observable<any> {
    const params = new HttpParams()
      .set('action', 'selectEntriesByAuthor')
      .set('email', author);
    return this.http.get<any>(this.apiUrl, { params });
  }

  searchByAuthor(email: string): Observable<any> {
    const params = new HttpParams()
      .set('action', 'searchByAuthor')
      .set('email', email);
    return this.http.get<any>(this.apiUrl, { params });
  }
  getEntriesByTitle(title: string): Observable<any> {
    const params = new HttpParams()
      .set('action', 'selectEntriesByTitle')
      .set('title', title);
    return this.http.get<any>(this.apiUrl, { params });
  }

  insertEntry(title: string, comment: string, date: string): Observable<any> {
    const params = new HttpParams()
      .set('action', 'insertEntry')
      .set('email', localStorage.getItem('email') || '')
      .set('title', title)
      .set('comment', comment)
      .set('date', date);
    return this.http.get<any>(this.apiUrl, { params });
  }

  updateEntry(
    id: number,
    title: string,
    comment: string,
    date: string
  ): Observable<any> {
    const params = new HttpParams()
      .set('action', 'updateEntry')
      .set('id', id.toString())
      .set('email', localStorage.getItem('email') || '')
      .set('title', title)
      .set('comment', comment)
      .set('date', date);
    return this.http.get<any>(this.apiUrl, { params });
  }
  loginCheck(email: string, password: string): Observable<any> {
    const params = new HttpParams()
      .set('action', 'checkUser')
      .set('email', email)
      .set('password', password);
    return this.http.get<any>(this.apiUrl, { params });
  }

  deleteEntry(id: number): Observable<any> {
    const params = new HttpParams().set('action', 'deleteEntry').set('id', id);
    return this.http.get<any>(this.apiUrl, { params });
  }
}
