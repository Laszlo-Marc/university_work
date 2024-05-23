import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AddEntryComponent } from './add-entry.component';

describe('AddEntryComponent', () => {
  let component: AddEntryComponent;
  let fixture: ComponentFixture<AddEntryComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [AddEntryComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(AddEntryComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
