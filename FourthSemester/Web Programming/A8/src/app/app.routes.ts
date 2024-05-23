import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AddEntryComponent } from './add-entry/add-entry.component';
import { LoginComponent } from './login/login.component';
import { ProfileComponent } from './profile/profile.component';
import { RemoveEntryComponent } from './remove-entry/remove-entry.component';
import { UpdateEntryComponent } from './update-entry/update-entry.component';
import { ViewEntriesComponent } from './view-entries/view-entries.component';

export const routes: Routes = [
  { path: '', redirectTo: 'login', pathMatch: 'full' },
  { path: 'login', component: LoginComponent },
  { path: 'profile', component: ProfileComponent },
  { path: 'view-entries', component: ViewEntriesComponent },
  { path: 'add-entry', component: AddEntryComponent },
  { path: 'remove-entry', component: RemoveEntryComponent },
  { path: 'update-entry', component: UpdateEntryComponent },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule],
})
export class AppRoutingModule {}
