/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { StroustrupWikiComponent } from './stroustrup-wiki.component';

describe('StroustrupWikiComponent', () => {
  let component: StroustrupWikiComponent;
  let fixture: ComponentFixture<StroustrupWikiComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ StroustrupWikiComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(StroustrupWikiComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

