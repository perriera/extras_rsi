/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { FrequentlyRequestedPapers1Component } from './frequently-requested-papers-1.component';

describe('FrequentlyRequestedPapers1Component', () => {
  let component: FrequentlyRequestedPapers1Component;
  let fixture: ComponentFixture<FrequentlyRequestedPapers1Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ FrequentlyRequestedPapers1Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(FrequentlyRequestedPapers1Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

