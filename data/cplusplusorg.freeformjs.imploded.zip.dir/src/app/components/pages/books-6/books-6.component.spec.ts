/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { Books6Component } from './books-6.component';

describe('Books6Component', () => {
  let component: Books6Component;
  let fixture: ComponentFixture<Books6Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ Books6Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(Books6Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

