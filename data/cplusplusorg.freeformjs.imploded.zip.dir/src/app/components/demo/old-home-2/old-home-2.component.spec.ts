/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { OldHome2Component } from './old-home-2.component';

describe('OldHome2Component', () => {
  let component: OldHome2Component;
  let fixture: ComponentFixture<OldHome2Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ OldHome2Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(OldHome2Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

