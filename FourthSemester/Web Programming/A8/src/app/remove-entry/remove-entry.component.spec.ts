import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RemoveEntryComponent } from './remove-entry.component';

describe('RemoveEntryComponent', () => {
  let component: RemoveEntryComponent;
  let fixture: ComponentFixture<RemoveEntryComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [RemoveEntryComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(RemoveEntryComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
