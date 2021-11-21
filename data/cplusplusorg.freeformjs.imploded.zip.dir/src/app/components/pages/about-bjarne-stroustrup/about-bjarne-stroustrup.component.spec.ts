/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { AboutBjarneStroustrupComponent } from './about-bjarne-stroustrup.component';

describe('AboutBjarneStroustrupComponent', () => {
  let component: AboutBjarneStroustrupComponent;
  let fixture: ComponentFixture<AboutBjarneStroustrupComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ AboutBjarneStroustrupComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(AboutBjarneStroustrupComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

