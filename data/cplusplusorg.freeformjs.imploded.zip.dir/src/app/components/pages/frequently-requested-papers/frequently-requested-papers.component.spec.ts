/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { FrequentlyRequestedPapersComponent } from './frequently-requested-papers.component';

describe('FrequentlyRequestedPapersComponent', () => {
  let component: FrequentlyRequestedPapersComponent;
  let fixture: ComponentFixture<FrequentlyRequestedPapersComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ FrequentlyRequestedPapersComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(FrequentlyRequestedPapersComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

