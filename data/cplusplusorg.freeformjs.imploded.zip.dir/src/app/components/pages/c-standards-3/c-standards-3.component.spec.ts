/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { CStandards3Component } from './c-standards-3.component';

describe('CStandards3Component', () => {
  let component: CStandards3Component;
  let fixture: ComponentFixture<CStandards3Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CStandards3Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(CStandards3Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

