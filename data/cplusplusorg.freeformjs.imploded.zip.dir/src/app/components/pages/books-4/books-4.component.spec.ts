/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { Books4Component } from './books-4.component';

describe('Books4Component', () => {
  let component: Books4Component;
  let fixture: ComponentFixture<Books4Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ Books4Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(Books4Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

