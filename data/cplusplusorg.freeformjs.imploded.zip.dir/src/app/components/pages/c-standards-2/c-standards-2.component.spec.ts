/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { CStandards2Component } from './c-standards-2.component';

describe('CStandards2Component', () => {
  let component: CStandards2Component;
  let fixture: ComponentFixture<CStandards2Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CStandards2Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(CStandards2Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

