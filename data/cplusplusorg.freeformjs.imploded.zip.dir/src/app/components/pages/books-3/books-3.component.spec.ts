/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { Books3Component } from './books-3.component';

describe('Books3Component', () => {
  let component: Books3Component;
  let fixture: ComponentFixture<Books3Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ Books3Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(Books3Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

