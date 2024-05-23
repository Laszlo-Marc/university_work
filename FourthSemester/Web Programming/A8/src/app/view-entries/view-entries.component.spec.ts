import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ViewEntriesComponent } from './view-entries.component';

describe('ViewEntriesComponent', () => {
  let component: ViewEntriesComponent;
  let fixture: ComponentFixture<ViewEntriesComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [ViewEntriesComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(ViewEntriesComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
