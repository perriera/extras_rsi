/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { CppBooksComponent } from './cpp-books.component';

describe('CppBooksComponent', () => {
  let component: CppBooksComponent;
  let fixture: ComponentFixture<CppBooksComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CppBooksComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(CppBooksComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

