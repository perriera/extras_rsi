/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { Books1Component } from './books-1.component';

describe('Books1Component', () => {
  let component: Books1Component;
  let fixture: ComponentFixture<Books1Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ Books1Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(Books1Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

