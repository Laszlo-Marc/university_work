// login.component.ts
import { CommonModule } from '@angular/common';
import { Component } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { DataService } from '../data.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css'],
  standalone: true,
  imports: [FormsModule, CommonModule],
})
export class LoginComponent {
  email: string = '';
  password: string = '';
  errorMessage: string = '';

  constructor(private dataService: DataService, private router: Router) {}

  login() {
    const loginData = {
      email: this.email,
      password: this.password,
      action: 'checkUser',
    };

    this.dataService.loginCheck(loginData.email, loginData.password).subscribe(
      (data) => {
        if (
          data['email'] === loginData.email &&
          data['password'] === loginData.password
        ) {
          localStorage.setItem('email', loginData.email);
          this.router.navigate(['profile']);
        } else {
          console.log(data);
          this.errorMessage = 'Invalid email or password';
        }
      },
      (error) => {
        console.error('Error logging in', error);
      }
    );
  }

  cancel() {
    this.router.navigate(['/']);
  }
}
