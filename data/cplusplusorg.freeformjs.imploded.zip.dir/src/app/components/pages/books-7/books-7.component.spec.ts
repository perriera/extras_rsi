/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { Books7Component } from './books-7.component';

describe('Books7Component', () => {
  let component: Books7Component;
  let fixture: ComponentFixture<Books7Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ Books7Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(Books7Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

