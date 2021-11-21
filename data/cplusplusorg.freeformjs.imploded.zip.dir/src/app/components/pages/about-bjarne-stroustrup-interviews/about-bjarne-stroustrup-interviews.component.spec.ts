/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { AboutBjarneStroustrupInterviewsComponent } from './about-bjarne-stroustrup-interviews.component';

describe('AboutBjarneStroustrupInterviewsComponent', () => {
  let component: AboutBjarneStroustrupInterviewsComponent;
  let fixture: ComponentFixture<AboutBjarneStroustrupInterviewsComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ AboutBjarneStroustrupInterviewsComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(AboutBjarneStroustrupInterviewsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

