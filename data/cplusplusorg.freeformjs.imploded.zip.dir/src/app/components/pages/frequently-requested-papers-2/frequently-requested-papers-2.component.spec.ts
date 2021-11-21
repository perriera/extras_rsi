/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { FrequentlyRequestedPapers2Component } from './frequently-requested-papers-2.component';

describe('FrequentlyRequestedPapers2Component', () => {
  let component: FrequentlyRequestedPapers2Component;
  let fixture: ComponentFixture<FrequentlyRequestedPapers2Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ FrequentlyRequestedPapers2Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(FrequentlyRequestedPapers2Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

