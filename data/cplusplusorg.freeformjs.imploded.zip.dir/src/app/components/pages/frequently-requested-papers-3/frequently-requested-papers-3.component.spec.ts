/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { FrequentlyRequestedPapers3Component } from './frequently-requested-papers-3.component';

describe('FrequentlyRequestedPapers3Component', () => {
  let component: FrequentlyRequestedPapers3Component;
  let fixture: ComponentFixture<FrequentlyRequestedPapers3Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ FrequentlyRequestedPapers3Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(FrequentlyRequestedPapers3Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

