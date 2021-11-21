/* tslint:disable:no-unused-variable */
import { async, ComponentFixture, TestBed } from '@angular/core/testing';
import { By } from '@angular/platform-browser';
import { DebugElement } from '@angular/core';

import { LambdaExpressionsComponent } from './lambda-expressions.component';

describe('LambdaExpressionsComponent', () => {
  let component: LambdaExpressionsComponent;
  let fixture: ComponentFixture<LambdaExpressionsComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ LambdaExpressionsComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(LambdaExpressionsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});

