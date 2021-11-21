/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { Books8Component } from './books-8.component';

describe('Books8Component', () => {
  let component: Books8Component;
  let fixture: ComponentFixture<Books8Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ Books8Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(Books8Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

