/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { FrequentlyRequestedPapers4Component } from './frequently-requested-papers-4.component';

describe('FrequentlyRequestedPapers4Component', () => {
  let component: FrequentlyRequestedPapers4Component;
  let fixture: ComponentFixture<FrequentlyRequestedPapers4Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ FrequentlyRequestedPapers4Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(FrequentlyRequestedPapers4Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

