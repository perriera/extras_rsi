/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { Books5Component } from './books-5.component';

describe('Books5Component', () => {
  let component: Books5Component;
  let fixture: ComponentFixture<Books5Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ Books5Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(Books5Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

