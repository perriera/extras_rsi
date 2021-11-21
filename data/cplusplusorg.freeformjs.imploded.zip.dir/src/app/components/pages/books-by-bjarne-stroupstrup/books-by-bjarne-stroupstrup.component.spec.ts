/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { BooksByBjarneStroupstrupComponent } from './books-by-bjarne-stroupstrup.component';

describe('BooksByBjarneStroupstrupComponent', () => {
  let component: BooksByBjarneStroupstrupComponent;
  let fixture: ComponentFixture<BooksByBjarneStroupstrupComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ BooksByBjarneStroupstrupComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(BooksByBjarneStroupstrupComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

