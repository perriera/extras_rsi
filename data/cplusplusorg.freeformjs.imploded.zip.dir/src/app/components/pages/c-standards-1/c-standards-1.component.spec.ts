/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { CStandards1Component } from './c-standards-1.component';

describe('CStandards1Component', () => {
  let component: CStandards1Component;
  let fixture: ComponentFixture<CStandards1Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ CStandards1Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(CStandards1Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

